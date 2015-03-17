/*
 *   Copyright (c) 2013, Klaus Pototzky
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

#ifndef PLAYGROUND_CXXBLAS_LEVEL3_SYMM_TCC
#define PLAYGROUND_CXXBLAS_LEVEL3_SYMM_TCC 1

#include <cxxblas/cxxblas.h>

namespace cxxblas {

#ifdef HAVE_CLBLAS

// ssymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const float &alpha,
      const flens::device_ptr<const float, flens::StorageType::OpenCL> A, IndexType ldA,
      const flens::device_ptr<const float, flens::StorageType::OpenCL> B, IndexType ldB,
      const float &beta,
      flens::device_ptr<float, flens::StorageType::OpenCL> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasSsymm");

    cl_int status = CLBLAS_IMPL(Ssymm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                       m, n, alpha,
                                       A.get(), A.getOffset(), ldA,
                                       B.get(), B.getOffset(), ldB, 
                                       beta,
                                       C.get(),C.getOffset(), ldC, 
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);

    flens::checkStatus(status);
    
}

// dsymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const double &alpha,
      const flens::device_ptr<const double, flens::StorageType::OpenCL> A, IndexType ldA,
      const flens::device_ptr<const double, flens::StorageType::OpenCL> B, IndexType ldB,
      const double &beta,
      flens::device_ptr<double, flens::StorageType::OpenCL> C, IndexType ldC)

{
    CXXBLAS_DEBUG_OUT("clAmdBlasDsymm");

    cl_int status = CLBLAS_IMPL(Dsymm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                       m, n, alpha,
                                       A.get(), A.getOffset(), ldA,
                                       B.get(), B.getOffset(), ldB, 
                                       beta,
                                       C.get(),C.getOffset(), ldC, 
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);

    flens::checkStatus(status);
}

// csymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const ComplexFloat &alpha,
      const flens::device_ptr<const ComplexFloat, flens::StorageType::OpenCL> A, IndexType ldA,
      const flens::device_ptr<const ComplexFloat, flens::StorageType::OpenCL> B, IndexType ldB,
      const ComplexFloat &beta,
      flens::device_ptr<ComplexFloat, flens::StorageType::OpenCL> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasCsymm");

    cl_int status = CLBLAS_IMPL(Csymm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                       m, n, *(reinterpret_cast<const cl_float2*>(&alpha)),
                                       A.get(), A.getOffset(), ldA,
                                       B.get(), B.getOffset(), ldB, 
                                       *(reinterpret_cast<const cl_float2*>(&beta)),
                                       C.get(), C.getOffset(), ldC,
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);

    flens::checkStatus(status);
}

// zsymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const ComplexDouble &alpha,
      const flens::device_ptr<const ComplexDouble, flens::StorageType::OpenCL> A, IndexType ldA,
      const flens::device_ptr<const ComplexDouble, flens::StorageType::OpenCL> B, IndexType ldB,
      const ComplexDouble &beta,
      flens::device_ptr<ComplexDouble, flens::StorageType::OpenCL> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasZsymm");
    
    cl_int status = CLBLAS_IMPL(Zsymm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                       m, n, *(reinterpret_cast<const cl_double2*>(&alpha)),
                                       A.get(), A.getOffset(), ldA,
                                       B.get(), B.getOffset(), ldB, 
                                       *(reinterpret_cast<const cl_double2*>(&beta)),
                                       C.get(), C.getOffset(), ldC,
                                       1, flens::OpenCLEnv::getQueuePtr(),
                                       0, NULL, NULL);
    flens::checkStatus(status);
}
    
#endif // HAVE_CLBLAS

#ifdef HAVE_CUBLAS

// ssymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const float &alpha,
      const flens::device_ptr<const float, flens::StorageType::CUDA> A, IndexType ldA,
      const flens::device_ptr<const float, flens::StorageType::CUDA> B, IndexType ldB,
      const float &beta,
      flens::device_ptr<float, flens::StorageType::CUDA> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("cublasSsymm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        symm(ColMajor, side, upLo, n, m,
             alpha, A, ldA, B, ldB, beta, C, ldC);
        return;
    }
    cublasStatus_t status = cublasSsymm(flens::CudaEnv::getHandle(), CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), 
                                        m, n, &alpha,
                                        A.get(), ldA,
                                        B.get(), ldB,
                                        &beta, C.get(), ldC);
    flens::checkStatus(status);
}

// dsymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const double &alpha,
      const flens::device_ptr<const double, flens::StorageType::CUDA> A, IndexType ldA,
      const flens::device_ptr<const double, flens::StorageType::CUDA> B, IndexType ldB,
      const double &beta,
      flens::device_ptr<double, flens::StorageType::CUDA> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("cublasDsymm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        symm(ColMajor, side, upLo, n, m,
             alpha, A, ldA, B, ldB, beta, C, ldC);
        return;
    }
    cublasStatus_t status = cublasDsymm(flens::CudaEnv::getHandle(), CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), 
                                        m, n, &alpha,
                                        A.get(), ldA,
                                        B.get(), ldB,
                                        &beta, C.get(), ldC);  
    flens::checkStatus(status);
}
// csymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const ComplexFloat &alpha,
      const flens::device_ptr<const ComplexFloat, flens::StorageType::CUDA> A, IndexType ldA,
      const flens::device_ptr<const ComplexFloat, flens::StorageType::CUDA> B, IndexType ldB,
      const ComplexFloat &beta,
      flens::device_ptr<ComplexFloat, flens::StorageType::CUDA> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("cublasCsymm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        symm(ColMajor, side, upLo, n, m,
             alpha, A, ldA, B, ldB, beta, C, ldC);
        return;
    }
    cublasStatus_t status = cublasCsymm(flens::CudaEnv::getHandle(), CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo),
                                        m, n, reinterpret_cast<const cuFloatComplex*>(&alpha),
                                        reinterpret_cast<const cuFloatComplex*>(A.get()), ldA,
                                        reinterpret_cast<const cuFloatComplex*>(B.get()), ldB,
                                        reinterpret_cast<const cuFloatComplex*>(&beta),
                                        reinterpret_cast<cuFloatComplex*>(C.get()), ldC);
                                        
    flens::checkStatus(status);
}

// zsymm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
symm(StorageOrder order, Side side, StorageUpLo upLo,
      IndexType m, IndexType n,
      const ComplexDouble &alpha,
      const flens::device_ptr<const ComplexDouble, flens::StorageType::CUDA> A, IndexType ldA,
      const flens::device_ptr<const ComplexDouble, flens::StorageType::CUDA> B, IndexType ldB,
      const ComplexDouble &beta,
      flens::device_ptr<ComplexDouble, flens::StorageType::CUDA> C, IndexType ldC)
{
    CXXBLAS_DEBUG_OUT("cublasZsymm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        symm(ColMajor, side, upLo, n, m,
             alpha, A, ldA, B, ldB, beta, C, ldC);
        return;
    }
    cublasStatus_t status = cublasZsymm(flens::CudaEnv::getHandle(),  CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), 
                                        m, n, reinterpret_cast<const cuDoubleComplex*>(&alpha),
                                        reinterpret_cast<const cuDoubleComplex*>(A.get()), ldA,
                                        reinterpret_cast<const cuDoubleComplex*>(B.get()), ldB,
                                        reinterpret_cast<const cuDoubleComplex*>(&beta),
                                        reinterpret_cast<cuDoubleComplex*>(C.get()), ldC);
    
    flens::checkStatus(status);
}

#endif // HAVE_CUBLAS

} // namespace cxxblas

#endif // PLAYGROUND_CXXBLAS_LEVEL3_SYMM_TCC
