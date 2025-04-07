<script lang="ts">
  import { onMount } from 'svelte';
  import type { FlagResponse, ApiResponse } from '$lib/api';
  
  let flagData: FlagResponse | null = null;
  let loading = true;
  let error: ApiResponse | null = null;
  
  onMount(async () => {
    try {
      const response = await fetch('http://backend:8000/api/protected/flag');
      
      if (response.ok) {
        flagData = await response.json();
      } else {
        error = await response.json();
      }
    } catch (err) {
      error = { message: "Error connecting to the API" };
      console.error(err);
    } finally {
      loading = false;
    }
  });
</script>

<div class="container">
  <div class="card">
    <h1>Secret Gator Flag</h1>
    
    {#if loading}
      <div class="loading">
        <p>Loading...</p>
      </div>
    {:else if error}
      <div class="error">
        <h2>Access Denied</h2>
        <p>{error.message}</p>
        <div class="hint">
          <p><strong>Hint:</strong> Only swamp creatures can access this page. Maybe there's a way to convince the API that you're a server-side middleware process...</p>
        </div>
      </div>
    {:else}
      <div class="success">
        <h2>Congratulations!</h2>
        <p>{flagData?.message}</p>
        <div class="flag">
          <p>{flagData?.flag}</p>
        </div>
      </div>
    {/if}
  </div>
</div>

<style>
  .loading, .error, .success {
    padding: 2rem;
    border-radius: 8px;
    text-align: center;
  }
  
  .error {
    background-color: #f8d7da;
    border: 1px solid #f5c6cb;
    color: #721c24;
  }
  
  .success {
    background-color: #d4edda;
    border: 1px solid #c3e6cb;
    color: #155724;
  }
  
  .flag {
    margin-top: 1.5rem;
    padding: 1rem;
    background-color: var(--swamp-dark);
    color: white;
    border-radius: 4px;
    font-family: monospace;
    font-size: 1.2rem;
  }
  
  .hint {
    margin-top: 1.5rem;
    padding: 1rem;
    background-color: #fff3cd;
    border: 1px solid #ffeeba;
    color: #856404;
    border-radius: 4px;
  }
  
  .hint-details {
    margin-top: 0.5rem;
    font-size: 0.9rem;
    color: #666;
  }
</style>
