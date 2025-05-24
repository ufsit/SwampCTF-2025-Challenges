from fastapi import FastAPI, Request, Depends, HTTPException, status
from starlette.middleware.base import BaseHTTPMiddleware
from fastapi.responses import JSONResponse
from fastapi.staticfiles import StaticFiles
from fastapi.middleware.cors import CORSMiddleware
import os

app = FastAPI()

# Enable CORS with proper configuration for the Docker network
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # In production, you'd specify frontend domain
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Load the flag from environment variable
FLAG = os.environ.get("FLAG", "swampCTF{b3w4r3_th3_m1ddl3w4r3}")

# Middleware to check authentication
class AuthMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request: Request, call_next):
        # Get all headers for debugging
        all_headers = dict(request.headers.items())
        print(f"Request headers: {all_headers}")
        
        # The vulnerability: bypass auth with a special header similar to the NextJS exploit
        # "x-middleware-subrequest: middleware" was the actual header used in the NextJS bypass vulnerability
        if "x-middleware-subrequest" in request.headers:
            # This mimics the actual NextJS exploit!
            print("Middleware bypass detected! Access granted.")
            return await call_next(request)
        
        # Check protected routes
        if request.url.path.startswith("/api/protected"):
            # No actual auth logic is implemented, which means no regular way to authenticate
            # This forces users to find the vulnerability
            print(f"Access denied to protected route: {request.url.path}")
            return JSONResponse(
                status_code=status.HTTP_401_UNAUTHORIZED,
                content={"message": "Unauthorized. Only swamp creatures allowed!"}
            )
        
        return await call_next(request)

# Add the auth middleware to the application
app.add_middleware(AuthMiddleware)

# Public endpoints
@app.get("/api/")
async def root():
    return {"message": "Welcome to the Swamp API!"}

# No login/signup endpoints exist - they are "under construction"
@app.get("/api/auth/status")
async def auth_status():
    return {
        "message": "Auth services are currently under construction. Please check back later!",
        "status": "unavailable"
    }

# Protected endpoint containing the flag
@app.get("/api/protected/flag")
async def get_flag():
    return {"message": "Congratulations, you found the secret middleware bypass!", "flag": FLAG}


if __name__ == "__main__":
    import uvicorn
    uvicorn.run("main:app", host="0.0.0.0", port=8000, reload=True)
