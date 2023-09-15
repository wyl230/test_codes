from fastapi import FastAPI
from . import routes

# cors problems
from fastapi.middleware.cors import CORSMiddleware

api = FastAPI()
origins = ["*"]
api.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


# 路由
api.include_router(routes.router, prefix="", tags=["real-paths"])
