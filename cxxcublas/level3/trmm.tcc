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

#ifndef PLAYGROUND_CXXBLAS_LEVEL3_TRMM_TCC
#define PLAYGROUND_CXXBLAS_LEVEL3_TRMM_TCC 1

#include <cxxblas/cxxblas.h>

namespace cxxblas {

#ifdef HAVE_CLBLAS

// strmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const float &alpha,
     const flens::device_ptr<const float, flens::StorageType::OpenCL> A, IndexType ldA,
     flens::device_ptr<float, flens::StorageType::OpenCL> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasStrmm");

    cl_int status = CLBLAS_IMPL_EX(Strmm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                          CLBLAS::getClblasType(transA), CLBLAS::getClblasType(diag),
                                          m, n, alpha,
                                          A.get(), A.getOffset(), ldA,
                                          B.get(), B.getOffset(), ldB, 
                                          1, flens::OpenCLEnv::getQueuePtr(),
                                          0, NULL, NULL);

    flens::checkStatus(status);
    
}

// dtrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const double &alpha,
     const flens::device_ptr<const double, flens::StorageType::OpenCL> A, IndexType ldA,
     flens::device_ptr<double, flens::StorageType::OpenCL> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasDtrmm");

    cl_int status = CLBLAS_IMPL_EX(Dtrmm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                          CLBLAS::getClblasType(transA), CLBLAS::getClblasType(diag),
                                          m, n, alpha,
                                          A.get(), A.getOffset(), ldA,
                                          B.get(), B.getOffset(), ldB, 
                                          1, flens::OpenCLEnv::getQueuePtr(),
                                          0, NULL, NULL);

    flens::checkStatus(status);
}

// ctrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const ComplexFloat &alpha,
     const flens::device_ptr<const ComplexFloat, flens::StorageType::OpenCL> A, IndexType ldA,
     flens::device_ptr<ComplexFloat, flens::StorageType::OpenCL> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasCtrmm");

    cl_int status = CLBLAS_IMPL_EX(Ctrmm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                          CLBLAS::getClblasType(transA), CLBLAS::getClblasType(diag),
                                          m, n, *(reinterpret_cast<const cl_float2*>(&alpha)),
                                          A.get(), A.getOffset(), ldA,
                                          B.get(), B.getOffset(), ldB, 
                                          1, flens::OpenCLEnv::getQueuePtr(),
                                          0, NULL, NULL);

    flens::checkStatus(status);
}

// ztrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const ComplexDouble &alpha,
     const flens::device_ptr<const ComplexDouble, flens::StorageType::OpenCL> A, IndexType ldA,
     flens::device_ptr<ComplexDouble, flens::StorageType::OpenCL> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("clAmdBlasZtrmm");
    
    cl_int status = CLBLAS_IMPL_EX(Ztrmm)(CLBLAS::getClblasType(order), CLBLAS::getClblasType(side), CLBLAS::getClblasType(upLo),
                                          CLBLAS::getClblasType(transA), CLBLAS::getClblasType(diag),
                                          m, n, *(reinterpret_cast<const cl_double2*>(&alpha)),
                                          A.get(), A.getOffset(), ldA,
                                          B.get(), B.getOffset(), ldB,
                                          1, flens::OpenCLEnv::getQueuePtr(),
                                          0, NULL, NULL);

    flens::checkStatus(status);
}
    
#endif // HAVE_CLBLAS

#ifdef HAVE_CUBLAS

// strmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const float &alpha,
     const flens::device_ptr<const float, flens::StorageType::CUDA> A, IndexType ldA,
     flens::device_ptr<float, flens::StorageType::CUDA> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("cublasStrmm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        trmm(ColMajor, side, upLo, transA, diag, n, m,
             alpha, A, ldA, B, ldB);
        return;
    }
    cublasStatus_t status = cublasStrmm(flens::CudaEnv::getHandle(),  CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), CUBLAS::getCublasType(transA),
                                        CUBLAS::getCublasType(diag),
                                        m, n, &alpha,
                                        A.get(), ldA,
                                        B.get(), ldB,
                                        B.get(), ldB);
    flens::checkStatus(status);
}

// dtrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const double &alpha,
     const flens::device_ptr<const double, flens::StorageType::CUDA> A, IndexType ldA,
     flens::device_ptr<double, flens::StorageType::CUDA> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("cublasDtrmm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        trmm(ColMajor, side, upLo, transA, diag, n, m,
             alpha, A, ldA, B, ldB);
        return;
    }
    cublasStatus_t status = cublasDtrmm(flens::CudaEnv::getHandle(),  CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), CUBLAS::getCublasType(transA),
                                        CUBLAS::getCublasType(diag),
                                        m, n, &alpha,
                                        A.get(), ldA,
                                        B.get(), ldB,
                                        B.get(), ldB);    
    flens::checkStatus(status);
}
// ctrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const ComplexFloat &alpha,
     const flens::device_ptr<const ComplexFloat, flens::StorageType::CUDA> A, IndexType ldA,
     flens::device_ptr<ComplexFloat, flens::StorageType::CUDA> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("cublasCtrmm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        trmm(ColMajor, side, upLo, transA, diag, n, m,
             alpha, A, ldA, B, ldB);
        return;
    }
    cublasStatus_t status = cublasCtrmm(flens::CudaEnv::getHandle(),  CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), CUBLAS::getCublasType(transA),
                                        CUBLAS::getCublasType(diag),
                                        m, n, reinterpret_cast<const cuFloatComplex*>(&alpha),
                                        reinterpret_cast<const cuFloatComplex*>(A.get()), ldA,
                                        reinterpret_cast<const cuFloatComplex*>(B.get()), ldB,
                                        reinterpret_cast<cuFloatComplex*>(B.get()), ldB);
                                        
    flens::checkStatus(status);
}

// ztrmm
template <typename IndexType>
typename If<IndexType>::isBlasCompatibleInteger
trmm(StorageOrder order, Side side, StorageUpLo upLo,
     Transpose transA, Diag diag,
     IndexType m, IndexType n, const ComplexDouble &alpha,
     const flens::device_ptr<const ComplexDouble, flens::StorageType::CUDA> A, IndexType ldA,
     flens::device_ptr<ComplexDouble, flens::StorageType::CUDA> B, IndexType ldB)
{
    CXXBLAS_DEBUG_OUT("cublasZtrmm");
    
    if (order==RowMajor) {
        side = (side==Left) ? Right : Left;
        upLo = (upLo==Upper) ? Lower : Upper;
        trmm(ColMajor, side, upLo, transA, diag, n, m,
             alpha, A, ldA, B, ldB);
        return;
    }
    cublasStatus_t status = cublasZtrmm(flens::CudaEnv::getHandle(),  CUBLAS::getCublasType(side),
                                        CUBLAS::getCublasType(upLo), CUBLAS::getCublasType(transA),
                                        CUBLAS::getCublasType(diag),
                                        m, n, reinterpret_cast<const cuDoubleComplex*>(&alpha),
                                        reinterpret_cast<const cuDoubleComplex*>(A.get()), ldA,
                                        reinterpret_cast<const cuDoubleComplex*>(B.get()), ldB,
                                        reinterpret_cast<cuDoubleComplex*>(B.get()), ldB);
    
    flens::checkStatus(status);
}

#endif // HAVE_CUBLAS

} // namespace cxxblas

#endif // PLAYGROUND_CXXBLAS_LEVEL3_TRMM_TCC
