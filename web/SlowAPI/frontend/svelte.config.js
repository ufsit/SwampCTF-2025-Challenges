import adapter from '@sveltejs/adapter-static';
import { vitePreprocess } from '@sveltejs/vite-plugin-svelte';

/** @type {import('@sveltejs/kit').Config} */
const config = {
	// Consult https://svelte.dev/docs/kit/integrations
	// for more information about preprocessors
	preprocess: vitePreprocess(),

	kit: {
		// Use the static adapter for deployment
		adapter: adapter({
			// Build to the 'build' directory for consistency with the Dockerfile
			fallback: 'index.html',
			out: 'build'
		})
	}
};

export default config;