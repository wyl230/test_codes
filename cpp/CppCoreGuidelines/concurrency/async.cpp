struct Reading {
  int day;
};

bool validate(const vector<Reading> &);
Graph<Temp_node> temperature_gradients(const vector<Reading> &);
Image altitude_map(const vector<Reading> &);
// ...

void process_readings(const vector<Reading> &surface_readings) {
  auto h1 = async([&] {
    if (!validate(surface_readings))
      throw Invalid_data{};
  });
  auto h2 = async([&] { return temperature_gradients(surface_readings); });
  auto h3 = async([&] { return altitude_map(surface_readings); });
  // ...
  h1.get();
  auto v2 = h2.get();
  auto v3 = h3.get();
  // ...
}
