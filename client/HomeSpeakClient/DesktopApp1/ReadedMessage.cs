

public class ReadedMessage
{
    public int type { get; set; }
    public Data[] data { get; set; }
}

public class Data
{
    public string timestamp { get; set; }
    public string message { get; set; }
    public string roomID { get; set; }
    public string userID { get; set; }
}
