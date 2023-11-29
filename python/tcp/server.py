import socket

# 指定主机和端口
host = "0.0.0.0"  # 可以使用0.0.0.0监听所有可用网络接口
port = 12345

# 创建一个TCP套接字
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 绑定套接字到指定的主机和端口
server_socket.bind((host, port))

# 开始监听传入的连接请求
server_socket.listen(5)  # 5表示等待连接的最大数量

print(f"正在监听 {host}:{port} 端口...")

while True:
    # 接受客户端连接
    client_socket, client_address = server_socket.accept()
    print(f"接受来自 {client_address} 的连接")

    # 从客户端接收数据
    data = client_socket.recv(1024)  # 一次最多接收1024字节数据
    if not data:
        break

    print(f"接收到的数据: {data.decode('utf-8')}")

    # 可以在这里对数据进行处理

    # 发送响应数据到客户端
    response = "你好，客户端！"
    client_socket.send(response.encode("utf-8"))

    # 关闭客户端连接
    client_socket.close()

# 关闭服务器套接字
server_socket.close()
