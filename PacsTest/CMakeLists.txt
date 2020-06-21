cmake_minimum_required (VERSION 3.8)

add_executable (PacsTest "PacsTest.cpp")

target_link_libraries (PacsTest DicomScu dcmnet dcmdata dcmjpeg dcmjpls ijg8 ijg12 ijg16 charls oflog ofstd Ws2_32 Iphlpapi Netapi32)
