 <?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "test_ros";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT coordX,coordY FROM test_coord ORDER BY id_coord DESC limit 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo  $row["coordX"]. ";" . $row["coordY"];
    }
} else {
    echo "0 results";
}
$conn->close();
?> 
