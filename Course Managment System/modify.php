<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string)$_POST["student_id"];
    $email = $_POST["email"];
    $password = $_POST["password"];
    $type = (string)$_POST["type"];
    $name = $_POST["name"];
    $dept_name = (string)$_POST["dept_name"];
    // Returns and update the email from the account table by matching student_ids and student table
    $sql_existing_email = "SELECT email FROM student WHERE student_id = '$student_id'";
    $result = $conn->query($sql_existing_email);
    $row = $result->fetch_assoc();
    $existing_email = $row['email'];
    
    $sql_student = "UPDATE student SET name = '$name', email = '$email', dept_name = '$dept_name' WHERE student_id = '$student_id'";

    if ($conn->query($sql_student) === TRUE) {
        echo "Information updated successfully!<br>";

        $sql_account = "UPDATE account SET email = '$email', password = '$password', type = '$type' WHERE email = '$existing_email'";
        if ($conn->query($sql_account) === TRUE) {
            echo "Account email updated!";
        } else {
            echo "Error updating account email: " . $conn->error;
        }

    } else {
        echo "Error updating student information: " . $conn->error;
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
    <a href="student_main_page.php?student_id=<?php echo $student_id; ?>"><button>Student Main Page</button></a>
</body>
</html>
