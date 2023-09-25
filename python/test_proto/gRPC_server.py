import grpc
from concurrent import futures
import time
import example_pb2
import example_pb2_grpc


class GreeterServicer(example_pb2_grpc.GreeterServicer):
    def SayHello(self, request, context):
        return example_pb2.Greeting(message=f"Hello, {request.message}!")


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    example_pb2_grpc.add_GreeterServicer_to_server(GreeterServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("Server started on port 50051")
    try:
        while True:
            time.sleep(3600)
    except KeyboardInterrupt:
        server.stop(0)


if __name__ == "__main__":
    serve()
