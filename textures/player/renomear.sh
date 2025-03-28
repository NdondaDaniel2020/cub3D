#!/bin/bash

# Verifica se há arquivos de imagem no diretório
shopt -s nullglob
images=(*.xpm *.jpg *.jpeg *.png *.gif *.bmp *.JPG *.JPEG *.PNG *.GIF *.BMP)

if [ ${#images[@]} -eq 0 ]; then
    echo "Nenhuma imagem encontrada no diretório atual."
    exit 1
fi

# Contador para a numeração
count=1

# Loop através de todas as imagens
for img in "${images[@]}"; do
    # Obtém a extensão do arquivo
    extension="${img##*.}"
    
    # Converte a extensão para minúsculas (opcional)
    extension=$(echo "$extension" | tr '[:upper:]' '[:lower:]')
    
    # Novo nome do arquivo
    new_name="mgun_$count.$extension"
    
    # Renomeia o arquivo
    mv -- "$img" "$new_name"
    
    echo "Renomeado: $img -> $new_name"
    
    # Incrementa o contador
    ((count++))
done

echo "Renomeação concluída. Total de imagens renomeadas: $((count-1))"
