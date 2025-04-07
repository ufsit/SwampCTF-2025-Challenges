// API helper functions

// Use relative paths - the nginx proxy will handle routing API requests to the backend
const API_BASE_URL = '';

// Generic fetch function
export async function fetchApi<T>(endpoint: string): Promise<T> {
  try {
    const response = await fetch(`${API_BASE_URL}${endpoint}`);
    
    if (!response.ok) {
      throw new Error(`API error: ${response.status}`);
    }
    
    return await response.json() as T;
  } catch (error) {
    console.error('API fetch error:', error);
    throw error;
  }
}

// Type definitions for API responses
export interface ApiResponse {
  message: string;
}

export interface AuthStatusResponse extends ApiResponse {
  status: string;
}

export interface FlagResponse extends ApiResponse {
  flag: string;
}