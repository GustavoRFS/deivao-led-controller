<script lang="ts">
  import { onMount } from "svelte";
  import type { Color } from "../../@types/Color";
  import "./index.css";
  export let percentage: number;
  export let color: Color;
  export let onMove: (percentage: number) => void;

  export let onClick: () => void;

  let lastTouch: number;

  let gradientMaker: HTMLElement;

  onMount(() => {
    gradientMaker = document.querySelector(".gradient-maker");
  });

  function onTouchMove({ touches }) {
    const gradientMakerWidth = gradientMaker?.offsetWidth;
    const gradientMakerLeft = gradientMaker?.offsetLeft - 20;

    const touch = touches[0].pageX;

    if (touch < gradientMakerLeft) return;
    if (touch > gradientMakerLeft + gradientMakerWidth + 40) return;

    if (!lastTouch) lastTouch = touch;

    const offsetX = touches[0].pageX - lastTouch;
    lastTouch = touches[0].pageX;

    move(offsetX);
  }

  function onMouseMove({ offsetX, x }) {
    if (x === 0 || !isDragging) return;

    move(offsetX - 10);
  }

  function move(offsetX: number) {
    const gradientMakerWidth = gradientMaker?.offsetWidth;
    percentage += (100 * offsetX) / gradientMakerWidth;

    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    setTimeout(() => onMove(percentage), 0);
  }

  let isDragging = false;

  const handleClick = (event: MouseEvent) => {
    event?.stopPropagation();

    isDragging = true;

    onClick?.(event);
  };

  const stopDragging = () => {
    isDragging = false;
  };
</script>

<div
  class="color-square"
  style={`left:${percentage}%`}
  on:mousedown={handleClick}
  on:mouseleave={stopDragging}
  on:mouseup={stopDragging}
  on:touchmove={onTouchMove}
  on:touchend={() => (lastTouch = undefined)}
  on:mousemove={onMouseMove}
>
  <div
    class="color-display"
    style={`background:rgb(${color.r},${color.g},${color.b})`}
  />
  <svg class="svg-arrow">
    <polyline points="0,0 12.5,12 25,0" class="svg-arrow-line" />
  </svg>
</div>
