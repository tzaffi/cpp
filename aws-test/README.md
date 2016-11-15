To configure your project, simply run the following:

```
cmake –Daws-sdk-cpp_DIR=<path to your SDK build> <path to your source>
```

In our case we have

* ~**SDK build path**: `/Users/zeph/cpp/aws-sdk-cpp`~
* **SDK build path**: `/Users/zeph/cpp/aws`
* **source path**: `./`

Therefore:

```
cd build
cmake -Daws-sdk-cpp_DIR=/Users/zeph/cpp/aws/build ../
make
```
