add_executable(ControllerTest)

target_sources(ControllerTest PRIVATE
    BacktrackingControllerTest.cpp
    )

target_link_libraries(ControllerTest PRIVATE
        mm_solver_lib
        Catch2::Catch2WithMain
        )


add_test(
        NAME ControllerTest
        COMMAND ControllerTest
)