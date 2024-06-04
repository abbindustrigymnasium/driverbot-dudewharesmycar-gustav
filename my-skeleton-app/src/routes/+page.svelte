<script lang="ts">
    import { onMount } from "svelte";
    import { onSend, startConnect, startDisconnect } from "../stors/Mqtt-Store.js";
    import { isConnected } from "../stors/Store.js";
  
    let recording = false;
    let recordedInputs = [];
    let lastTimestamp = 0;
  
    onMount(() => {
      document.addEventListener("keydown", handleKeydown);
    });
  
    //Recording
    function handleKeydown(event: KeyboardEvent) {
      const key = event.key.toUpperCase();
      
      // includes exakt keys 
      if (["A", "S", "W", "D","Q"].includes(key)) {
        console.log(`${key} key pressed`);
        onSend("WromWrom", key);
        
        // Logs inputs and the time betwean the inputs 
        if (recording) {
          const currentTimestamp = Date.now();
          const timeElapsed = lastTimestamp ? currentTimestamp - lastTimestamp : 0;
          recordedInputs.push({ key, timeElapsed });
          console.log(recordedInputs);
          lastTimestamp = currentTimestamp;
        }
        
        //Ends the recording 
      } else if (key === "R") {
        recording = !recording;
        if (recording) {
          lastTimestamp = Date.now(); // Reset the timestamp at the start of recording
        } else {
          console.log("Recorded inputs:", recordedInputs.map(input => `${input.key}: ${input.timeElapsed}ms`));
        }
        
        //plays the recording when T is prest
      } else if (key === "T") {
        if (!recording && recordedInputs.length > 0) {
          playRecording();
        }
      }
    }
  
    function playRecording() {
      let playbackTimestamp = 0;
  
      recordedInputs.forEach(input => {
        playbackTimestamp += input.timeElapsed;
        setTimeout(() => {
          console.log(`Replaying: ${input.key} after ${input.timeElapsed}ms`);
          onSend("WromWrom", input.key);
        }, playbackTimestamp);
      });
    }
  </script>
  
 
  <main>
    <!--Change icon when connected-->
    {#if !$isConnected} 
      <button on:click={startConnect} type="button" class="connected" style="background-image: url('NotConected.png'); background-size: contain; background-repeat: no-repeat; height: 60px; width: 60px;"></button>
    {:else}
      <button on:click={startDisconnect} type="button" class="connected" style="background-image: url('Conected.png'); background-size: contain; background-repeat: no-repeat; height: 40px; width: 40px;"></button>
    {/if}
  </main>
  
  <style lang="postcss">
    figure {
      @apply flex relative flex-col;
    }
  
    figure svg,
    .img-bg {
      @apply w-64 h-64; md:w-80; md:h-80;
    }
  
    .img-bg {
      @apply absolute z-[-1] rounded-full blur-[50px] transition-all;
      animation: pulse 5s cubic-bezier(0, 0, 0, 0.5) infinite,
        glow 5s linear infinite;
    }
  
    @keyframes glow {
      0% {
        @apply bg-primary-400/50;
      }
      33% {
        @apply bg-secondary-400/50;
      }
      66% {
        @apply bg-tertiary-400/50;
      }
      100% {
        @apply bg-primary-400/50;
      }
    }
  
    @keyframes pulse {
      50% {
        transform: scale(1.5);
      }
    }
  </style>
  