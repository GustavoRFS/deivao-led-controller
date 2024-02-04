<script lang="ts">
  import { Icon } from "@smui/common";
  import IconButton from "@smui/icon-button/src/IconButton.svelte";
  import Paper from "@smui/paper/src/Paper.svelte";
  import Ripple from "@smui/ripple";
  import type { Favorite, Gradient } from "../../shared/@types/Color";
  import colorStore from "../../shared/stores/colors";

  import "./index.css";
  import serial from "../../services/serial";

  let isDeleting = false;
  let favorites: Favorite[] = [];

  colorStore.subscribe((state) => {
    favorites = state.favorites;
  });

  const toggleIsDeleting = () => (isDeleting = !isDeleting);

  const favoriteColorStyle = (favorite: Favorite) => {
    if (favorite.type === "color") {
      return `background:rgb(${favorite.value.r},${favorite.value.g},${favorite.value.b});`;
    } else {
      if (!favorite?.value) return "";

      let style = `background:linear-gradient(45deg`;

      (favorite?.value as Gradient[])?.forEach((gradient, index) => {
        style += `,rgb(${gradient.color.r},${gradient.color.g},${gradient.color.b}) ${gradient.percentage}%`;
      });

      return `${style})`;
    }
  };

  const changeColor = (favorite: Favorite) => () => {
    if (favorite.type === "color") {
      serial.sendMessage({ event: "color", data: favorite.value });
    } else {
      serial.sendMessage({ event: "gradient", data: favorite.value });
    }
  };

  const deleteColor = (indexToRemove: number) => {
    colorStore.update((state) => {
      const newFavorites = state.favorites.filter(
        (favorite, index) => index !== indexToRemove
      );
      return { ...state, favorites: newFavorites };
    });
  };
</script>

<div
  style="display:flex;flex-wrap:wrap;justify-content:center;gap:40px;padding:10px;"
>
  {#each favorites as favorite, index (index)}
    <div style="position:relative">
      <Paper variant="raised" style="padding:0;border-radius:4px">
        <div
          use:Ripple={{ surface: true, color: "primary" }}
          class="favorite-color"
          style={favoriteColorStyle(favorite)}
          on:click={changeColor(favorite)}
        />
        {#if isDeleting}
          <div
            on:click={() => deleteColor(index)}
            style="background-color:#f00;position:absolute;top:-10px;right:-10px;width:20px;height:20px;border-radius:10px;cursor:pointer"
          >
            <Icon
              style="font-size:18px;color:#fff;margin-top:1px"
              class="material-icons">delete</Icon
            >
          </div>
        {/if}
      </Paper>
    </div>
  {/each}
  <div style="position:fixed;right:20px;bottom:60px;">
    <IconButton on:click={toggleIsDeleting} color="primary"
      ><Icon class="material-icons">{isDeleting ? "check" : "delete"}</Icon
      ></IconButton
    >
  </div>
</div>
