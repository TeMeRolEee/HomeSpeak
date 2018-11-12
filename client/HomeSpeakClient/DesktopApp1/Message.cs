using System;

public class Message
{
    int type;
    int id;
    string token;
    string msg;
    int roomID;
    int userID;


	public Message()
	{
	}

    public int Type { get => type; set => type = value; }
    public int Id { get => id; set => id = value; }
    public string Token { get => token; set => token = value; }
}
