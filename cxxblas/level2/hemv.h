/*
 *   Copyright (c) 2010, Michael Lehn
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

#ifndef CXXBLAS_LEVEL2_HEMV_H
#define CXXBLAS_LEVEL2_HEMV_H 1

#include <cxxblas/drivers/drivers.h>
#include <cxxblas/typedefs.h>

#define HAVE_CXXBLAS_HEMV 1

namespace cxxblas {

template <typename IndexType, typename ALPHA, typename MA, typename VX,
          typename BETA, typename VY>
    void
    hemv(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         const ALPHA &alpha,
         const MA *A, IndexType ldA,
         const VX *x, IndexType incX,
         const BETA &beta,
         VY *y, IndexType incY);

#ifdef HAVE_CBLAS

// chemv
template <typename IndexType>
    typename If<IndexType>::isBlasCompatibleInteger
    hemv(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         const ComplexFloat &alpha,
         const ComplexFloat *A, IndexType ldA,
         const ComplexFloat *x, IndexType incX,
         const ComplexFloat &beta,
         ComplexFloat *y, IndexType incY);

// zhemv
template <typename IndexType>
    typename If<IndexType>::isBlasCompatibleInteger
    hemv(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         const ComplexDouble &alpha,
         const ComplexDouble *A, IndexType ldA,
         const ComplexDouble *x, IndexType incX,
         const ComplexDouble &beta,
         ComplexDouble *y, IndexType incY);

#endif // HAVE_CBLAS

#ifdef HAVE_CUBLAS

// chemv
template <typename IndexType>
    typename If<IndexType>::isBlasCompatibleInteger
    hemv(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         const ComplexFloat &alpha,
         const thrust::device_ptr<const ComplexFloat> A, IndexType ldA,
         const thrust::device_ptr<const ComplexFloat> x, IndexType incX,
         const ComplexFloat &beta,
         thrust::device_ptr<ComplexFloat> y, IndexType incY);


// zhemv
template <typename IndexType>
    typename If<IndexType>::isBlasCompatibleInteger
    hemv(StorageOrder order, StorageUpLo upLo,
         IndexType n,
         const ComplexDouble &alpha,
         const thrust::device_ptr<const ComplexDouble> A, IndexType ldA,
         const thrust::device_ptr<const ComplexDouble> x, IndexType incX,
         const ComplexDouble &beta,
         thrust::device_ptr<ComplexDouble> y, IndexType incY);

#endif // HAVE_CUBLAS

} // namespace cxxblas

#endif // CXXBLAS_LEVEL2_HEMV_H
