import grpc
import example_pb2
import example_pb2_grpc


def run():
    channel = grpc.insecure_channel("localhost:50051")
    stub = example_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(example_pb2.Greeting(message="World"))
    print(f"Greeter client received: {response.req}")


if __name__ == "__main__":
    run()
