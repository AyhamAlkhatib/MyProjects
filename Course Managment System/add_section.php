<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $course_id = $_POST['course_id'];
    $section_id = $_POST['section_id'];
    $semester = $_POST['semester'];
    $year = $_POST['year'];
    $instructor_id = $_POST['instructor_id'];
    $classroom_id = $_POST['classroom_id'];
    $time_slot_id = $_POST['time_slot_id'];

    // Check if time slot has two sections scheduled
    // Query counts number of sections for the time slot
    $sql = "SELECT COUNT(*) AS count FROM section WHERE time_slot_id = '$time_slot_id' AND year = '$year' AND semester ='$semester'";
    $result = $conn->query($sql);
    $row = $result->fetch_assoc();
    // If less than two sections in this timeslot, continue
    if ($row['count'] < 2) {
        // Check if the section_id is already used by counting the number of sections for the section id provided
        // for that semster and year
        $sql_section = "SELECT COUNT(*) AS count FROM section WHERE section_id = '$section_id' AND year = '$year' AND semester = '$semester'";
        $result_section = $conn->query($sql_section);
        $row_section = $result_section->fetch_assoc();

        if ($row_section['count'] == 0) {
            // Check if the instructor is already teaching two sections by counting the number of sections the instructor is teaching
            $sql_instructor = "SELECT COUNT(*) AS count FROM section WHERE instructor_id = '$instructor_id' AND year = '$year' AND semester = '$semester'";
            $result_instructor = $conn->query($sql_instructor);
            $row_instructor = $result_instructor->fetch_assoc();

            if ($row_instructor['count'] < 2) {
                $sql_time = "SELECT time_slot_id FROM section WHERE instructor_id = '$instructor_id' AND year = '$year' AND semester = '$semester'";
                $result_time = $conn->query($sql_time);
                
                // It first retrieves the instructor’s existing time slots and checks if the new slot is consecutive to any of them.
                $time_slot_order = ['TS1', 'TS2', 'TS3', 'TS4', 'TS5', 'TS6', 'TS7', 'TS8', 'TS9']; 
                $existing_slots = [];
                // existing slots instructor teaching
                while ($row_time = $result_time->fetch_assoc()) {
                    $existing_slots[] = $row_time['time_slot_id'];
                }

                $consecutive = count($existing_slots) == 0;
                // putting the time_slot_id the admin typed in a new_index and subtracting it by the existing time slot that
                // instructor is teaching and if it's 1 then they're consecutive and update consecutive to true
                if (!$consecutive) {
                    $new_TS = array_search($time_slot_id, $time_slot_order);
                    foreach ($existing_slots as $existing_slot) {
                        $existing_index = array_search($existing_slot, $time_slot_order);
                        if ($existing_index !== false && $new_TS !== false && abs($existing_index - $new_TS) == 1) {
                            $consecutive = true;
                            break;
                        }
                    }
                }

                if ($consecutive) {
                    $sql_insert = "INSERT INTO section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) 
                                   VALUES ('$course_id', '$section_id', '$semester', '$year', '$instructor_id', '$classroom_id', '$time_slot_id')";
                    if ($conn->query($sql_insert) === TRUE) {
                        echo "Section Inserted Successfully";
                        // Inserting into teacherTaught table to know which stores the sections instructor taught which contains fileds:
                        $sql_instructor_insert = "INSERT INTO teacherTaught (course_id, section_id, semester, year, instructor_id) 
                                                  VALUES ('$course_id', '$section_id', '$semester', '$year', '$instructor_id')";
                        if ($conn->query($sql_instructor_insert) !== TRUE) {
                            echo "Error inserting into teacherTaught: " . $conn->error;
                        }
                    } else {
                        echo "Error inserting into section: " . $conn->error;
                    }
                } else {
                    echo "Instructor’s schedule must have consecutive time slots.";
                    exit;
                }
            } else {
                echo "Instructor already teaching two sections.";
                exit;
            }
        } else {
            echo "Section is already being used for current semester and year.";
            exit;
        }
    } else {
        echo "Two sections already allocated for this time slot.<br>";
        exit;
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
</head>
<body>
    <br><br>
    <a href="admin_main_page.php">
        <button type="button">Admin Main Page</button>
    </a>
</body>
</html>