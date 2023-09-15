# 异步接受udp消息
import uvicorn

if __name__ == "__main__":
    uvicorn.run(
        app="src.app:api",
        host="0.0.0.0",
        reload=True,
        port=5001,
        log_level="info"
        # app="src.app:api", host="0.0.0.0", reload=True, port=5001, log_level="error"
    )
