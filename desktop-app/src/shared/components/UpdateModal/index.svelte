<script lang="ts">
  import SvelteMarkdown from "svelte-markdown";
  import Modal from "../Modal/index.svelte";
  import Button from "@smui/button";
  import { onMount } from "svelte";
  import LoadingIndicator from "../LoadingIndicator/index.svelte";
  import UpdatingModal from "../UpdatingModal/index.svelte";
  import {
    checkUpdate,
    installUpdate,
    onUpdaterEvent,
  } from "@tauri-apps/api/updater";

  export let isOpened: boolean;
  export let toggleModal: () => void;

  let loading = false;

  let updateLoading = false;

  let updateManifest = undefined;

  onMount(async () => {
    const { manifest } = await checkUpdate();

    updateManifest = manifest;
  });

  const onClickUpdate = async () => {
    loading = true;
    try {
      await installUpdate();
    } finally {
      loading = false;
      toggleModal();
    }
  };
</script>

<Modal {isOpened}>
  <div
    style="padding:10px 5px;max-height:80vh;text-align:start;display:flex;flex-direction:column;align-items:center"
  >
    <h2>Atualização Disponível</h2>
    <h2 style="margin-left:5%;align-self: flex-start;margin-top:10px">
      Versão: {updateManifest?.version}
    </h2>
    <h2 style="margin-left:5%;align-self: flex-start;margin-top:10px">
      Notas de atualização:
    </h2>
    <div style="width:90%;max-height:60%;overflow-y:auto;">
      <SvelteMarkdown options={{}} source={updateManifest.body} />
    </div>
    <div style="margin:10px 0px">
      <Button
        on:click={onClickUpdate}
        style="margin-right:10px"
        variant="raised"
        >{#if updateLoading}<LoadingIndicator loading={updateLoading} />
        {:else}Atualizar{/if}</Button
      ><Button on:click={toggleModal} variant="text">Fechar</Button>
    </div>
  </div>
  <LoadingIndicator {loading} />
  <UpdatingModal />
</Modal>
