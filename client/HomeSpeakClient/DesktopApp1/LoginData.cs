
public class LoginData
{
    private static LoginData instance = null;

    public int type { get; set; }
    public int id { get; set; }
    public string username { get; set; }
    public string token { get; set; }
    public string email { get; set; }
    public string password { get; set; }

    private LoginData()
    {
    }
    public static LoginData Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new LoginData();
            }
            return instance;
        }
    }
}

