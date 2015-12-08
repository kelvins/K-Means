#include "kmeans.h"

QVector<int> KMeans::start(int k, QVector<double> coluna1, QVector<double> coluna2)
{
    this->K = k;
    this->col1 = coluna1;
    this->col2 = coluna2;

    iteracoes = 0;

    return KMEANS();
}

QVector<int> KMeans::KMEANS()
{
    QVector<double> xKs;
    QVector<double> yKs;

    QVector<double> grupo[K];

    QVector<double> distancia[col1.length()];

    double maxCol1 = achaMaximo(col1);
    double minCol1 = achaMinimo(col1);
    double maxCol2 = achaMaximo(col2);
    double minCol2 = achaMinimo(col2);

    /*xKs.append( -0.04 );
    xKs.append( 0.04 );
    xKs.append( 0.02 );

    yKs.append( 0.03 );
    yKs.append( -0.015 );
    yKs.append( 0.03 );
    xKinicial = xKs;
    yKinicial = yKs;*/

    // 1º Passo: gera os valores random para os centróides
    for (int var = 0; var < K; ++var)
    {
        xKs.append( random(minCol1, maxCol1) );
        yKs.append( random(minCol2, maxCol2) );

        xKinicial = xKs;
        yKinicial = yKs;
    }

    QVector<int> positions;

    for (int count = 0; count < 999999999; ++count)
    {
        for (int var = 0; var < col1.length(); ++var)
            distancia[var].clear();

        // 2º Passo: calcula a distância de cada ponto para todos os centróides
        for (int var = 0; var < col1.length(); ++var)
            for (int temp = 0; temp < K; ++temp)
                distancia[var].append( sqrt( pow((xKs.at(temp)-col1.at(var)), 2) + pow((yKs.at(temp)-col2.at(var)), 2) ) ); // raiz quadrada( (Xb-Xa)^2 + (Yb-Ya)^2 )


        // 3º Passo: calcula a qual centróide pertence cada dado/ponto de acordo com a distância
        bool trocou = false; // Flag usada para saber se houve troca de grupo em algum dado

        guardaGrupo.clear();
        for (int var = 0; var < K; ++var)
            grupo[var].clear();

        for (int var = 0; var < col1.length(); ++var)
        {
            double min = distancia[var].at(0); // Assume que a primera posição é a menor
            int position = 0; // Pega a posição do menor valor (K mais próximo)

            for (int temp = 1; temp < K; ++temp)
            {
                // Testa a distância do dado atual para cada K
                if( distancia[var].at(temp) < min ) // Se for menor que a distância mínima, marca como mais próximo
                {
                    min = distancia[var].at(temp);
                    position = temp;
                }
            }

            if( count == 0 )
            {
                positions.append( position ); // Guarda o K de cada dado
                trocou = true;
            }
            else
            {
                if( positions.at(var) != position )
                {
                    positions[var] = position;
                    trocou = true;
                }
            }
            grupo[position].append( var ); // Grava a posição do dado no grupo a que ele pertence
            guardaGrupo.append(position);
        }

        if( trocou == false )
            break;

        // 4º Passo: recalcula a posição de todos os centróides de acordo com a média dos dados
        // que pertencem a ele e retorna ao passo 2 até convergir
        for (int var = 0; var < K; ++var)
        {
            if( grupo[var].length() > 1 ) // Se o grupo do centróide tem mais que 1 dado
            {
                double mediaX = 0;
                double mediaY = 0;
                for (int temp = 0; temp < grupo[var].length(); ++temp)
                {
                    mediaX += col1.at( grupo[var].at(temp) );
                    mediaY += col2.at( grupo[var].at(temp) );
                }
                mediaX = mediaX/grupo[var].length();
                mediaY = mediaY/grupo[var].length();

                xKs[var] = mediaX;
                yKs[var] = mediaY;
            }
        }
        xKfinal.clear();
        yKfinal.clear();
        xKfinal = xKs;
        yKfinal = yKs;

        iteracoes++;
    }


    // Preenche um vetor com a quantidade de dados em cada grupo para retornar
    QVector<int> grupos;
    for (int var = 0; var < K; ++var)
    {
        grupos.append( 0 );
        for (int temp = 0; temp < grupo[var].length(); ++temp)
        {
            grupos[var] += 1;
        }
    }

    return grupos;
}

double KMeans::achaMaximo(QVector<double> vetor)
{
    double max = vetor.at(0);
    for (int var = 1; var < vetor.length(); ++var)
        if( vetor.at(var) > max )
            max = vetor.at(var);
    return max;
}

double KMeans::achaMinimo(QVector<double> vetor)
{
    double min = vetor.at(0);
    for (int var = 1; var < vetor.length(); ++var)
        if( vetor.at(var) < min )
            min = vetor.at(var);
    return min;
}

double KMeans::random(double valor1, double valor2)
{
    /*if( valor2 < valor1 )
        return 0;*/
   /* if( valor2 > valor1 )
        return (rand() % ((valor2+1)-valor1) + valor1);

    return (rand() % ((valor1+1)-valor2) + valor2);*/
    double f = (double)rand() / (RAND_MAX + 1.0);
    return valor1 + f * (valor2 - valor1);
}
QVector<int> KMeans::getGuardaGrupo() const
{
    return guardaGrupo;
}

int KMeans::getIteracoes() const
{
    return iteracoes;
}

QVector<double> KMeans::getYKfinal() const
{
    return yKfinal;
}

QVector<double> KMeans::getXKfinal() const
{
    return xKfinal;
}

QVector<double> KMeans::getYKinicial() const
{
    return yKinicial;
}

QVector<double> KMeans::getXKinicial() const
{
    return xKinicial;
}
