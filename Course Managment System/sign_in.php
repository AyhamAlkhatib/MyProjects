<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["email"];
    $password = $_POST["password"];
    // Returning the type of whoever is logging in
    $sql = "SELECT type FROM account WHERE email = '$email' AND password = '$password'";
    $result = $conn->query($sql);
    $row = $result->fetch_assoc();
    $user_type = $row['type'];

    if ($result->num_rows > 0 && $user_type == 'admin') {
        header("Location: admin_main_page.php");
    } else if ($result->num_rows > 0 && $user_type == 'student') {
        // Get their student_id from the student table and redirect it to the student_main_page along with the student_id
        $sql_student_id = $conn->query("SELECT student_id FROM student WHERE email = '$email'");
        
        if ($sql_student_id->num_rows > 0) {
            $student_data = $sql_student_id->fetch_assoc();
            $student_id = $student_data['student_id']; 

            header("Location: student_main_page.php?student_id=$student_id");
        } else {
            echo "Student not found!";
        }
    } elseif ($result->num_rows > 0 && $user_type == 'instructor') {
        $sql_instructor_id = $conn->query("SELECT instructor_id FROM instructor WHERE email = '$email'");
        
        if ($sql_instructor_id->num_rows > 0) {
            $instructor_data = $sql_instructor_id->fetch_assoc();
            $instructor_id = $instructor_data['instructor_id'];

            header("Location: instructor_main_page.php?instructor_id=$instructor_id");
        } else {
            echo "Instructor not found!";
        }
    } else {
        echo "Invalid email or password or type.";
    }
}

$conn->close();
?>