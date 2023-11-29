from loguru import logger

print = logger.info
warn = logger.warning
debug = logger.debug
error = logger.error
trace = logger.trace
trace(5)
print(1)
warn(2)
debug(3)
error(4)
