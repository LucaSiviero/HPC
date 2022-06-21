#! /bin/sh

docker run -it -v /home/luca/HPC/project:/root/project -v/opt/intel/oneapi:/opt/intel/oneapi --gpus=all luigicrisci/sycl_cuda11.4
