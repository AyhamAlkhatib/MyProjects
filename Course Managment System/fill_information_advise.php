<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];
$sections = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string)$_POST['student_id'];
    $instructor_id = (string)$_POST['instructor_id'];
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Modify Advise Information</title>
</head>
<body>

    <h2>Modify Advise Information!</h2>
    
    <form action="modify_advise_information.php" method="post">
        <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
        <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">

        <!-- Qualifier Dropdown -->
        <label for="qualifier">Qualifier:</label>
        <select name="qualifier" id="qualifier" required>
            <option value="qualified">Qualified</option>
            <option value="unqualified">Unqualified</option>
        </select><br><br>

        <!-- Start and End Dates for Instructor 1 -->
        <label for="proposal_defence_date">Proposal Defence Date:</label>
        <input type="date" name="proposal_defence_date" required><br><br>

        <label for="dissertation_defence_date">Dissertation Defence Date:</label>
        <input type="date" name="dissertation_defence_date"><br><br>

        <!-- Submit Button -->
        <button type="submit">Update!</button>
    </form>

</body>
</html>