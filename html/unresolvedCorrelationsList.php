<!-- This page is loaded into resolveCorrelations.php using jQuery's load() function -->
<div class="row">
	<div class="col-12">
		<h5>Unresolved correlations list</h5>
		<table class="table">
		<tr>
			<th>Source Bank Account</th>
			<th>How it was spent description</th>
			<td>Number of transactions with this unresolved correlation</th>
		</tr>
		<?php
		$cor_query = "select imp.src_bank_account, imp.description, count(*) as cnt from imported_data as imp left join correlations_table as ct on ct.";
		$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
		if (mysqli_connect_error()) {
			die("Failed to connect to db: " . mysqli_connect_error());
		}
		try {
			$sel = $conn->query($cor_query);
			while($row = $sel->fetch_assoc()) {
				echo "<tr>";
					
				echo "</tr>";
			}
		} catch(Exception $e) {
			echo "Error getting list of unresolved correlations: " . $e->getMessage();
		}
		?>
		</table>
		
	</div>
</div>

