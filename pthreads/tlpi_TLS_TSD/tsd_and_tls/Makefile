#include ../Makefile.inc

#GEN_EXE = detached_attrib one_time_init prod_condvar prod_no_condvar \
	simple_thread strerror_test strerror_test_tsd \
	thread_cancel thread_cleanup thread_incr thread_incr_mutex \
	thread_multijoin

#LINUX_EXE = strerror_test_tls

EXE = strerror_test strerror_test_tsd strerror_test_tls

all : ${EXE}

#allgen : ${GEN_EXE}

#CFLAGS = ${IMPL_CFLAGS} ${IMPL_THREAD_FLAGS}
#LDLIBS = ${IMPL_LDLIBS} ${IMPL_THREAD_FLAGS}
CFLAGS = -Wall
CFLAGS_DBG = -Wall -DDEBUG -g -ggdb -O0
LDLIBS = -pthread

strerror_test: strerror_test.o strerror.o
	${CC} -o $@ strerror_test.o strerror.o ${CFLAGS} ${LDLIBS}

strerror_test_tsd: strerror_test.o strerror_tsd.o
	${CC} -o $@ strerror_test.o strerror_tsd.o ${CFLAGS} ${LDLIBS}

strerror_test_tls: strerror_test.o strerror_tls.o
	${CC} -o $@ strerror_test.o strerror_tls.o ${CFLAGS} ${LDLIBS}

clean : 
	${RM} -f ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${LPLIB}		# True as a rough approximation
