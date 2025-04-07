<script lang="ts">
	import '../app.css';

	let { children } = $props();
</script>

<div class="app">
  <nav class="nav">
    <div class="nav-container">
      <div class="nav-logo">
        <span>🐊 SwampAPI</span>
      </div>
      <div class="nav-links">
        <a href="/">Home</a>
        <a href="/login">Login</a>
        <a href="/flag">Secret Flag</a>
      </div>
    </div>
  </nav>

  <main>
    {@render children()}
  </main>

  <footer class="footer">
    <p>&copy; {new Date().getFullYear()} SwampCTF - Gator Research Institute</p>
  </footer>
</div>

<style>
  .app {
    display: flex;
    flex-direction: column;
    min-height: 100vh;
  }

  main {
    flex: 1;
  }
</style>