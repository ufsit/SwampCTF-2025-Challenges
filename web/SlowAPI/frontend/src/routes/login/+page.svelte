<script lang="ts">
  import { onMount } from 'svelte';
  
  let authStatus = "Loading...";
  
  onMount(async () => {
    try {
      const response = await fetch('http://localhost:8000/api/auth/status');
      const data = await response.json();
      authStatus = data.message;
    } catch (error) {
      authStatus = "Error connecting to the API";
      console.error(error);
    }
  });
</script>

<div class="container">
  <div class="construction card">
    <h1>🚧 Under Construction 🚧</h1>
    
    <pre class="gator-ascii">
                 .-._   _ _ _ _ _ _ _ _
     .-''-.__.-'00  '-' ' ' ' ' ' ' ' '-.
     '.___ '    .   .--_'-' '-' '-' _'-' '._
      V: V 'vv-'   '_   '.       .'  _..' '.'.
        '=.____.=_.--'   :_.__.__:_   '.   : :
                (((____.-'        '-.  /   : :
                                    (((-'\ .' /
                                  _____..'  .'
                                 '-._____.-'
                 GATOR CONSTRUCTION TEAM
    </pre>
    
    <p>Our login and registration system is currently unavailable.</p>
    <p class="status">{authStatus}</p>
    <p>The swamp developers are working diligently to complete this feature.</p>
    <p>Please check back later!</p>
  </div>
</div>

<style>
  .construction {
    text-align: center;
    max-width: 600px;
    margin: 0 auto;
  }
  
  .status {
    font-weight: bold;
    margin: 1.5rem 0;
    padding: 1rem;
    background-color: var(--swamp-water);
    color: white;
    border-radius: 4px;
  }
  
  .gator-ascii {
    font-family: monospace;
    font-size: 12px;
    white-space: pre;
    line-height: 1;
    margin: 1.5rem auto;
    color: var(--swamp-green);
  }
</style>