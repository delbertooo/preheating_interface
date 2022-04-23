


```bash
mkdir preheating_interface/main/lib
cd preheating_interface/main/lib
ln -s ../../../../libscheduling libscheduling
ln -s ../../../../libpreheatinginterface libpreheatinginterface


docker compose up -d
# or with custom overrides
docker compose -f docker-compose.yml -f usbserial.yml up -d

docker compose exec shell /opt/esp/entrypoint.sh bash
```


```bash
# on my mac
ser2net -d -l -C '9090:raw:0:/dev/cu.usbserial-0001:115200 8DATABITS NONE 1STOPBIT'
#socat tcp-listen:9090 pty,link=/dev/cu.usbserial-0001
# in shell
socat pty,link=/dev/virtualcom0 tcp:host.docker.internal:9090
#-p socket://host.docker.internal:9090
```



python -m esptool --chip esp32 -p COM5 -b 460800 --before=default_reset --after=hard_reset write_flash --flash_mode dio --flash_freq 40m --flash_size 2MB 0x1000 bootloader/bootloader.bin 0x10000 preheating_interface.bin 0x8000 partition_table/partition-table.bin


https://stackoverflow.com/questions/8304190/cmake-with-include-and-source-paths-basic-setup
https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/build_system/cmake/import_lib/main/CMakeLists.txt


https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c

https://github.com/espressif/esp-idf/blob/bcbef9a8db54d2deef83402f6e4403ccf298803a/examples/peripherals/adc/single_read/adc/main/adc1_example_main.c

