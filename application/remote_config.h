#ifndef REMOTE_CONFIG_H
#define REMOTE_CONFIG_H

#define REMOTE_TYPE_DT7 1
#define REMOTE_TYPE_I6X 2

/* Select one receiver, then rebuild and flash. I6X is observation only. */
#ifndef REMOTE_CONTROL_TYPE
#define REMOTE_CONTROL_TYPE REMOTE_TYPE_DT7
#endif

#if REMOTE_CONTROL_TYPE != REMOTE_TYPE_DT7 && REMOTE_CONTROL_TYPE != REMOTE_TYPE_I6X
#error "Unsupported REMOTE_CONTROL_TYPE"
#endif

#endif
