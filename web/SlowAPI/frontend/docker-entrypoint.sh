#!/bin/bash
set -e

# Set default BACKEND_URL if not provided
export BACKEND_URL=${BACKEND_URL:-http://backend:8000}

# Process nginx config templates
envsubst '${BACKEND_URL}' < /etc/nginx/templates/default.conf.template > /etc/nginx/conf.d/default.conf

# Start nginx
exec "$@"