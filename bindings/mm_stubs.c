/*
 * Copyright (c) 2015 Thomas Leonard <talex5@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdint.h>
#include <caml/mlvalues.h>
#define CONFIG_LIBUKALLOC_IFPAGES 1
#define CONFIG_LIBUKALLOC_IFSTATS 1
#include <uk/alloc.h>

CAMLprim value
stub_heap_get_pages_total(value unit) // noalloc
{
  struct uk_alloc *allocator;
  allocator = uk_alloc_get_default();
  return Val_long(allocator->totalmem_pages(allocator));
}

CAMLprim value
stub_heap_get_pages_used(value unit) // noalloc
{
  struct uk_alloc *allocator;
  allocator = uk_alloc_get_default();
  return Val_long(allocator->availmem_pages(allocator));
}

/* expose the virt_to_mfn macro for converting a "virtual address number"
 * (AKA "a pointer") to a machine frame number
*/
CAMLprim value
stub_virt_to_mfn(value page)
{
  CAMLparam1(page);
  CAMLlocal1(result);
  result = caml_copy_nativeint(virt_to_mfn(Nativeint_val(page)));
  CAMLreturn(result);
}
