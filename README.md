CPM seems to solve the fetching errors using traditional FetchConten.

However, nlohmann-json and libmysofa need to be compiled manually:
- mkdir build in respective directories,
- cmake -DCMAKE_BUILD_TYPE=Debug ..
- make 
