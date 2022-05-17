#! /bin/sh

docker run -it -v /home/luca/hpc/src:/root/src --gpus=all luigicrisci/sycl_cuda11.4
