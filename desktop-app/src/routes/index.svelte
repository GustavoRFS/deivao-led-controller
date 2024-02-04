<script lang="ts">
  import { Router, Route } from "svelte-navigator";
  import BottomTabNavigator from "../shared/components/BottomTabNavigator/index.svelte";
  import ColorSelection from "../features/ColorSelection/index.svelte";
  import Favorites from "../features/Favorites/index.svelte";
  import Gradient from "../features/Gradient/index.svelte";
  import IconButton from "@smui/icon-button";
  import { Icon } from "@smui/common";
  import SettingsModal from "../shared/components/SettingsModal/index.svelte";
  import themeStore from "../shared/stores/theme";
  import { checkUpdate, onUpdaterEvent } from "@tauri-apps/api/updater";
  import { onMount, onDestroy } from "svelte";
  import UpdateModal from "../shared/components/UpdateModal/index.svelte";

  const unlisten = async () =>
    await onUpdaterEvent(({ error, status }) => {
      // This will log all updater events, including status updates and errors.
      console.log("Updater event", error, status);
    });

  onMount(async () => {
    try {
      const { shouldUpdate } = await checkUpdate();
      if (shouldUpdate) {
        toggleUpdateModal();
      }
    } catch (error) {
      console.error(error);
    }
  });

  onDestroy(unlisten);

  let darkMode: boolean;

  let settingsOpened = false;
  const toggleSettingsModal = () => {
    settingsOpened = !settingsOpened;
  };

  let updateModalOpened = false;
  const toggleUpdateModal = () => {
    updateModalOpened = !updateModalOpened;
  };

  themeStore.subscribe((theme) => {
    darkMode = theme === "dark";
  });
</script>

<Router>
  <div
    style={`display:flex;flex-grow:1;justify-content:center;align-items:center;`}
  >
    <IconButton
      style="position:absolute;left:20px;top:10px"
      on:click={() =>
        themeStore.update((theme) => (theme === "dark" ? "light" : "dark"))}
    >
      <Icon class="material-icons">{darkMode ? "light_mode" : "dark_mode"}</Icon
      ></IconButton
    >
    <div style="position:absolute;right:20px;top:10px;">
      <!-- <IconButton on:click={toggleSettingsModal} color="primary"
        ><Icon class="material-icons">settings</Icon></IconButton
      > -->
    </div>
    <SettingsModal
      isOpened={settingsOpened}
      toggleModal={toggleSettingsModal}
    />
    <UpdateModal isOpened={updateModalOpened} toggleModal={toggleUpdateModal} />
    <!-- <Route path="/effects" component={EffectsSelection} /> -->
    <Route path="/favorites" component={Favorites} />
    <Route path="/gradient" component={Gradient} />
    <Route component={ColorSelection} />

    <BottomTabNavigator />
  </div>
</Router>
