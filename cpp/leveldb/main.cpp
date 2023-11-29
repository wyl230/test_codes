#include <iostream>
#include <leveldb/db.h>
#include <memory>

int main() {
  // 定义 LevelDB 数据库的路径
  std::string db_path = "./test.db";

  // LevelDB 实例
  leveldb::DB *db;

  // LevelDB 选项
  leveldb::Options options;
  options.create_if_missing = true;

  // 打开 LevelDB 数据库，如果不存在则创建
  leveldb::Status status = leveldb::DB::Open(options, db_path, &db);

  if (status.ok()) {
    // 写入数据
    leveldb::WriteOptions write_options;
    db->Put(write_options, "key1", "value1");
    db->Put(write_options, "key1", "value2");

    // 读取数据
    leveldb::ReadOptions read_options;
    std::string value;
    status = db->Get(read_options, "key1", &value);

    if (status.ok()) {
      std::cout << "Value for key1: " << value << std::endl;
    } else {
      std::cerr << "Error reading key1: " << status.ToString() << std::endl;
    }

    // 删除数据
    leveldb::WriteOptions delete_options;
    db->Delete(delete_options, "key1");

    // 关闭 LevelDB 数据库
    delete db;
  } else {
    std::cerr << "Error opening LevelDB: " << status.ToString() << std::endl;
  }

  return 0;
}
