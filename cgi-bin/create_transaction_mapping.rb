#!/usr/bin/ruby 

# versions of ruby libraries to connect
# dbd-mysql (0.4.4)
# dbi (0.4.5)
# mysql (2.9.1)
# uri ()
# htmlentiries ()

require "dbi"
require "uri"
# https://stackoverflow.com/questions/1600526/how-do-i-encode-decode-html-entities-in-ruby
require "htmlentities"


input_string = gets
input_string.strip!

print "Content-Type:application/json\n\n"

begin
	dbh = DBI.connect("DBI:Mysql:free_budget_db:localhost", "free_budget_conn", "badpassword")
	# var_pairs = input_string.split("&", -1)
	coder = HTMLEntities.new
	mapping_params = Hash[URI.decode_www_form(input_string)]
	decoded_mapping_params = Hash.new 
	mapping_params.each_pair { |ky, val| decoded_mapping_params[ky] = coder.decode(val)  }
	# insert statement
	sth = dbh.prepare("insert into correlations_table (src_bank_account, dst_description, src_line_type_id, dst_line_type_id, src_account_id, dst_account_id) VALUES (?, ?, ?, ?, ?, ?)")
	sth.execute(
	    decoded_mapping_params["srcBankAccountName"],
	    decoded_mapping_params["srcDesc"],
	    decoded_mapping_params["srcMappedLineType"],
	    decoded_mapping_params["dstMappedLineType"],
	    decoded_mapping_params["srcMappedAccount"],
	    decoded_mapping_params["dstMappedAccount"]
	)
	sth.finish
	dbh.commit
	print "{ \"input\": \"#{input_string}\" }"
rescue DBI::DatabaseError => e    
	print "{ \"error\": \"#{e.err}; #{e.errstr}\" }"
	dhb.rollback
ensure
	dbh.disconnect if dbh
end

