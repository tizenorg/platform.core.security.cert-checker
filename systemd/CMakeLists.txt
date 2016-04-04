INSTALL(
	FILES
		${PROJECT_SOURCE_DIR}/systemd/cert-checker.socket
		${PROJECT_SOURCE_DIR}/systemd/cert-checker.service
	DESTINATION
		${SYSTEMD_UNIT_DIR})
