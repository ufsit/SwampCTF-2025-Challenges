FROM node:18-alpine as build

WORKDIR /app

COPY package.json ./

RUN npm install

COPY . .

# Create a production build of the frontend
RUN npm run build

# Use nginx with a custom configuration for the proxy
FROM nginx:alpine

# Copy the built frontend files
COPY --from=build /app/build /usr/share/nginx/html

# Install envsubst for environment variable substitution
RUN apk add --no-cache bash

# Create a custom nginx config with proxy settings
RUN rm /etc/nginx/conf.d/default.conf
COPY nginx.conf /etc/nginx/templates/default.conf.template

# Create startup script to handle env var substitution and start nginx
COPY docker-entrypoint.sh /
RUN chmod +x /docker-entrypoint.sh

EXPOSE 3000

ENTRYPOINT ["/docker-entrypoint.sh"]
CMD ["nginx", "-g", "daemon off;"]