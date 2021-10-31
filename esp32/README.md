


```
docker compose up -d

docker compose exec shell /opt/esp/entrypoint.sh bash
```



python -m esptool --chip esp32 -p COM5 -b 460800 --before=default_reset --after=hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 bootloader/bootloader.bin 0x10000 hello_world.bin 0x8000 partition_table/partition-table.bin


https://stackoverflow.com/questions/8304190/cmake-with-include-and-source-paths-basic-setup
https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/build_system/cmake/import_lib/main/CMakeLists.txt


https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c

https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/peripherals/adc/single_read/adc/main/adc1_example_main.c

