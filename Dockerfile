FROM lifflander1/vt:alpine-final

COPY . /usr/src/detector

WORKDIR /usr/src

RUN /bin/bash -c 'source $HOME/.bashrc && \
 source /usr/share/spack/share/spack/setup-env.sh && \
 spack env activate clang-mpich && \
 export CC=clang && \
 export CXX=clang++ && \
 echo $HTTP_PROXY && \
 echo $HTTPS_PROXY && \
 echo $ALL_PROXY && \
 echo $http_proxy && \
 echo $https_proxy && \
 echo $all_proxy && \
 unset https_proxy &&  \
 unset http_proxy && \
 unset all_proxy && \
 unset HTTPS_PROXY && \
 unset HTTP_PROXY && \
 unset ALL_PROXY && \
 export DETECTOR=$PWD/detector && \
 export DETECTOR_BUILD=/usr/build/detector && \
 cd $DETECTOR_BUILD && \
 mkdir build && \
 cd build && \
 cmake -DCMAKE_INSTALL_PREFIX=$DETECTOR_BUILD/install -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_C_COMPILER=$CC $DETECTOR && \
 make && \
 make install'

COPY $DETECTOR_BUILD/ $DETECTOR_BUILD
