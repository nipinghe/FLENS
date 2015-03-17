/*
 *   Copyright (c) 2009, Michael Lehn
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PLAYGROUND_CXXBLAS_LEVEL2_SPR2_TCC
#define PLAYGROUND_CXXBLAS_LEVEL2_SPR2_TCC 1

#include <complex>
#include <cxxblas/cxxblas.h>

namespace cxxblas {

  
#ifdef HAVE_CLBLAS

// cher
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
spr2(StorageOrder order, StorageUpLo upLo,
      IndexType n,
      float alpha,
      const flens::device_ptr<const float, flens::StorageType::OpenCL> x, IndexType incX,
      const flens::device_ptr<const float, flens::StorageType::OpenCL> y, IndexType incY,
      flens::device_ptr<float, flens::StorageType::OpenCL> A)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasSspr2");

    cl_int status = CLBLAS_IMPL(Sspr2)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(upLo), 
                                       n,
                                       alpha,
                                       x.get(), x.getOffset(), incX,
                                       y.get(), y.getOffset(), incY,
                                       A.get(), A.getOffset(),
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);

    flens::checkStatus(status);  
}

// zher
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
spr2(StorageOrder order, StorageUpLo upLo,
      IndexType n,
      double alpha,
      const flens::device_ptr<const double, flens::StorageType::OpenCL> x, IndexType incX,
      const flens::device_ptr<const double, flens::StorageType::OpenCL> y, IndexType incY,
      flens::device_ptr<double, flens::StorageType::OpenCL> A)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasDspr2");

    cl_int status = CLBLAS_IMPL(Dspr2)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(upLo), 
                                       n,
                                       alpha,
                                       x.get(), x.getOffset(), incX,
                                       y.get(), y.getOffset(), incY,
                                       A.get(), A.getOffset(),
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);

    flens::checkStatus(status); 
}

#endif // HAVE_CLBLAS
    
    

#ifdef HAVE_CUBLAS

// cspr2
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
    spr2(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         float alpha,
         const flens::device_ptr<const float, flens::StorageType::CUDA> x, IndexType incX,
         const flens::device_ptr<const float, flens::StorageType::CUDA> y, IndexType incY,
         flens::device_ptr<float, flens::StorageType::CUDA> A)
{
    CXXBLAS_DEBUG_OUT("cublasSspr2");
    
    ASSERT (order==ColMajor);

    cublasStatus_t status = cublasSspr2(flens::CudaEnv::getHandle(), CUBLAS::getCublasType(upLo),
                                        n, 
                                        &alpha,
                                        x.get(), incX,
                                        y.get(), incY,
                                        A.get());
    
    flens::checkStatus(status);
}

// zspr2
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
spr2(StorageOrder order, StorageUpLo upLo,
      IndexType n,
      double alpha,
      const flens::device_ptr<const double, flens::StorageType::CUDA> x, IndexType incX,
      const flens::device_ptr<const double, flens::StorageType::CUDA> y, IndexType incY,
      flens::device_ptr<double, flens::StorageType::CUDA> A)
{
    CXXBLAS_DEBUG_OUT("cublasDspr2");
      
    ASSERT (order==ColMajor);

    cublasStatus_t status = cublasDspr2(flens::CudaEnv::getHandle(), CUBLAS::getCublasType(upLo),
                                        n, 
                                        &alpha,
                                        x.get(), incX,
                                        y.get(), incY,
                                        A.get());
    
    flens::checkStatus(status);
}

#endif // HAVE_CUBLAS



} // namespace cxxblas

#endif // PLAYGROUND_CXXBLAS_LEVEL2_SPR2_TCC
