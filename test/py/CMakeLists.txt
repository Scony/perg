add_custom_target(${PROJECT_NAME}-pytest-run
  COMMAND tox
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/test/py"
  VERBATIM
  )
