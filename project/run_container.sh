#! /bin/sh

docker run -it -v /home/luca/HPC/project:/root/project --gpus=all luigicrisci/sycl_cuda11.4
