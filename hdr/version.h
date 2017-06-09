/**
 **  Copyright 2017 Gustavo de Oliveira Silva (DIG)
 **
 **  Licensed under the Apache License, Version 2.0 (the "License");
 **  you may not use this file except in compliance with the License.
 **  You may obtain a copy of the License at
 **
 **      http://www.apache.org/licenses/LICENSE-2.0
 **
 **  Unless required by applicable law or agreed to in writing, software
 **  distributed under the License is distributed on an "AS IS" BASIS,
 **  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 **  See the License for the specific language governing permissions and
 **  limitations under the License.
 **
 */

#ifndef EASY_GETTEXT_VERSION

#define EASY_GETTEXT_VERSION_MAJOR 0
#define EASY_GETTEXT_VERSION_MINOR 1
#define EASY_GETTEXT_VERSION_REV 2

#define EASY_GETTEXT_str(a) #a
#define EASY_GETTEXT_xstr(a) EASY_GETTEXT_str(a)

#ifdef UNICODE_SUPPORT
#define EASY_GETTEXT_VERSION EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_MAJOR) "." EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_MINOR) "." EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_REV) "u"
#else
#define EASY_GETTEXT_VERSION EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_MAJOR) "." EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_MINOR) "." EASY_GETTEXT_xstr(EASY_GETTEXT_VERSION_REV)
#endif

#endif