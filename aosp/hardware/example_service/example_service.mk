# Add package to build with system
PRODUCT_PACKAGES += \
		com.service.exampleservice \
		com.example.api.aidl \
		ExampleApp \

PRODUCT_ARTIFACT_PATH_REQUIREMENT_ALLOWED_LIST += \
    	system/app/ExampleApp/%

# Define the path of sepolicy, our policy will be collected and build with system policy
BOARD_SEPOLICY_DIRS += \
		hardware/example_service/sepolicy/vendor \

# Define the path of framework compatibility matrix
DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE += \
		hardware/example_service/interfaces/framework_compatibility_matrix.xml \
