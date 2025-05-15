<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string)$_POST['student_id'];
    $instructor_id = (string)$_POST['instructor_id'];
    $qualifier = (string)$_POST['qualifier'];
    $proposal_defence_date = (string)$_POST['proposal_defence_date'];
    $dissertation_defence_date = (string)$_POST['dissertation_defence_date'];

    // TODO: modify infromation in PhD where matches student id
    $modify = $conn->query("UPDATE PhD SET qualifier = '$qualifier', proposal_defence_date = '$proposal_defence_date',
        dissertation_defence_date = '$dissertation_defence_date' WHERE student_id = '$student_id'");
    
    echo "Modified Advise Information!<br><br>";
    
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Modify Advise Information</title>
</head>
<body>
<a href="instructor_main_page.php?instructor_id=<?php echo $instructor_id; ?>"><button>Instructor Main Page</button></a>
</body>
</html>