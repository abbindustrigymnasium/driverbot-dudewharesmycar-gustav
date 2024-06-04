<script lang="ts">
    import { onMount } from 'svelte';
    import '../app.postcss';
    import { AppShell, AppBar } from '@skeletonlabs/skeleton';

    // Set to store currently pressed keys
    let pressedKeys = new Set();

    // Function to update the background color of keys based on pressed keys
    function updateKeyColors() {
        const keys = ['w', 'a', 's', 'd',];
        keys.forEach(key => {
            const element = document.querySelector(`.${key}-key`);
            if (pressedKeys.has(key)) {
                element.style.backgroundColor = 'orange';
            } else {
                element.style.backgroundColor = 'rgba(0, 101, 50, 0.808)';
            }
        });
    }
    
    // Event listener for keydown event
	onMount(() =>{
		window.addEventListener('keydown', (event) => {
    	    pressedKeys.add(event.key); // Add pressed key to the set
    	    updateKeyColors(); 
    	});
    	window.addEventListener('keyup', (event) => {
    	    pressedKeys.delete(event.key); // Remove released key from the set
    	    updateKeyColors(); 
    	});
	})
    
</script>



<AppShell>
    <svelte:fragment slot="header">
    </svelte:fragment>
    <!-- Page Route Content -->
    <slot />
    <!-- W,A,S,D keys -->
    <div class="w-key">W</div>
    <div class="a-key">A</div>
	<div class="q-key">D</div>
    <div class="s-key">S</div>
    <div class="d-key">D</div>
</AppShell>

    <!-- W,A,S,D keys appearance in the web page -->
<style>
    .w-key {
        position: fixed;
        bottom: 100px; 
        right: 80px; 
        background-color:rgba(0, 101, 50, 0.808); 
        color: #ffffff; /* Text color */
        padding: 10px 15px; 
        border-radius: 5px; 
        font-weight: bold; 
        font-size: 16px; 
    }
	.a-key {
        position: fixed;
        bottom: 35px;
        right: 130px; 
        background-color:rgba(0, 101, 50, 0.808); 
        color: #ffffff; /* Text color */
        padding: 10px 15px; 
        border-radius: 5px; 
        font-weight: bold; 
        font-size: 16px; 
    }
	.s-key {
        position: fixed;
        bottom: 35px; 
        right: 82px;
        background-color:rgba(0, 101, 50, 0.808);
        color: #ffffff; /* Text color */
        padding: 10px 15px; 
        border-radius: 5px; 
        font-weight: bold; 
        font-size: 16px; 
    }
	.d-key {
        position: fixed;
        bottom: 35px; 
        right: 30px; 
        background-color: rgba(0, 101, 50, 0.808); 
        color: #ffffff; /* Text color */
        padding: 10px 15px; 
        border-radius: 5px; 
        font-weight: bold; 
        font-size: 16px; 
    }
</style>
