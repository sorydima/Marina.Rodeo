/* Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 2021 Google LLC
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "../cachedb/test/test_cachedb.h"
#include "../lib/test/test_csv.h"
#include "../mem/test/test_malloc.h"
#include "../str.h"
#include "../ut.h"
#include "../lib/csv.h"

#include "../dprint.h"
#include "../globals.h"
#include "../lib/list.h"
#include "../sr_module.h"
#include "../sr_module_deps.h"

#include "../test/fuzz/fuzz_standalone.h"

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  // Ensure we have one byte for the "decider" variable
  if (size == 0) {
    return 0;
  }
  int decider = data[0];
  data++;
  size--;

  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  csv_record *ret = NULL;
  if ((decider % 2) == 0) {
    ret = parse_csv_record(_str(new_str));
  }
  else {
    ret = _parse_csv_record(_str(new_str), CSV_RFC_4180);
  }
  free_csv_record(ret);
  free(new_str);
  return 0;
}
