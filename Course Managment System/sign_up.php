<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["email"];
    $password = $_POST["password"];
    $type = "student";

        $sql = "INSERT INTO account (email, password, type) 
               VALUES ('$email', '$password', '$type')";
        if ($conn->query($sql) === TRUE) {
            echo "Registration Successful!"; 
        } else {
            echo "An error Occured.";
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
    <a href="student_registration.html"><button type="button">Fill Information</button></a>
</body>

</html>