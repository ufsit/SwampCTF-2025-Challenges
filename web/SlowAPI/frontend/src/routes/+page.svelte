<script lang="ts">
  import { onMount } from 'svelte';
  
  let apiStatus = "Loading...";
  
  import { fetchApi } from '$lib/api';
  
  onMount(async () => {
    try {
      const data = await fetchApi('/api/');
      apiStatus = data.message;
    } catch (error) {
      apiStatus = "Error connecting to the API";
      console.error(error);
    }
  });
</script>

<div class="container">
  <div class="card">
    <h1>Welcome to the SwampAPI</h1>
    <p>The premier API service for swamp creatures and gator enthusiasts.</p>
    
    <div class="alert alert-info">
      <p>API Status: {apiStatus}</p>
    </div>
    
    <h2>About SwampAPI</h2>
    <p>
      SwampAPI is a revolutionary service built for the swamp ecosystem. Our team of expert gators 
      has developed cutting-edge technology to connect various swamp systems and provide valuable data 
      to amphibious creatures across the wetlands.
    </p>
    
    <h2>Features</h2>
    <ul>
      <li>Real-time mud quality monitoring</li>
      <li>Gator tracking and social networking</li>
      <li>Swamp vegetation cataloging</li>
      <li>Lily pad reservation system</li>
      <li>Encrypted communication for private swamp matters</li>
    </ul>
    
    <div class="alert alert-warning">
      <p><strong>Note:</strong> Some of our services are currently under construction, including our authentication system. We apologize for any inconvenience.</p>
    </div>
  </div>
</div>

<style>
  ul {
    margin-left: 2rem;
    margin-bottom: 1.5rem;
  }
  
  .alert-warning {
    background-color: #f8d7da;
    color: #721c24;
    border: 1px solid #f5c6cb;
  }
  
  .alert-info {
    background-color: #d1ecf1;
    color: #0c5460;
    border: 1px solid #bee5eb;
  }
</style>