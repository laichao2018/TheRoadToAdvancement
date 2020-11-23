//
// Created by LaiChao on 2020/11/20.
//

#ifndef THEROADTOADVANCEMENT___OS_JUDGE_H
#define THEROADTOADVANCEMENT___OS_JUDGE_H


#ifdef                          __APPLE__
#define		my_int_min		INT64_MIN
#define		my_int_max		INT64_MAX
#endif // __APPLE__

#ifdef                          _linux
#define		my_int_min		INT64_MIN
#define		my_int_max		INT64_MAX
#endif // _linux

#ifdef                          _linux_
#define		my_int_min		INT64_MIN
#define		my_int_max		INT64_MAX
#endif // _linux_

#ifdef                          _WIN32
#define		my_int_min		INT_MIN
#define		my_int_max		INT_MAX
#endif // _WIN32

#ifdef                          _WIN64
#define		my_int_min		INT_MIN
#define		my_int_max		INT_MAX
#endif // _WIN64

#ifdef _MSC_VER
#define		my_int_min		INT_MIN
#define		my_int_max		INT_MAX
#endif // _MSC_VER

#endif //THEROADTOADVANCEMENT___OS_JUDGE_H
